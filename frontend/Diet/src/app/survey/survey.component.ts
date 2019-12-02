import { Component, OnInit } from '@angular/core';
import { SignInService } from '../sign-in.service';
import { Router } from '@angular/router';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { take } from 'rxjs/operators';

@Component({
  selector: 'app-survey',
  templateUrl: './survey.component.html',
  styleUrls: ['./survey.component.css']
})
export class SurveyComponent implements OnInit {
  title: string;
  survey = new FormGroup({
    email: new FormControl("", [Validators.required]),
    height: new FormControl("", [Validators.required]),
    weight: new FormControl("", [Validators.required]),
    gender: new FormControl("", [Validators.required]),
    DOB: new FormControl("", [Validators.required]),
    lvlOfActivity: new FormControl("", [Validators.required]),
    dietaryRestriction: new FormControl("", [Validators.required])
  });
  httpOptions = new HttpHeaders({
    'Content-Type': 'application/json',
    'user': ''
  })
  constructor(private signInService: SignInService, private router: Router, private http: HttpClient) {
    if(router.url == "/manage") {
      this.title = "Update your information!"
    } else {
      this.title = "Tell us more!";
    }
  }

  ngOnInit() {
  }
  submit() : void {
      console.log(this.survey.getRawValue())
      this.http.post("http://localhost:3000/survey",  { headers: this.httpOptions}).pipe(take(1)).subscribe(() => {})
      // this.http.post("http://localhost:3000/survey", this.survey.getRawValue(), { headers: this.httpOptions}).pipe(take(1)).subscribe(() => {})
      this.signInService.setIsLoggedIn(true);
      //this.router.navigate(["pick"]);
   }
}
