import { Component, OnInit } from '@angular/core';
import { SignInService } from '../sign-in.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-survey',
  templateUrl: './survey.component.html',
  styleUrls: ['./survey.component.css']
})
export class SurveyComponent implements OnInit {
  title: string;
  constructor(private signInService: SignInService, private router: Router) {
    if(router.url == "/manage") {
      this.title = "Update your information!"
    } else {
      this.title = "Tell us more!";
    }
  }

  ngOnInit() {
  }
  submit() : void {
      this.signInService.setIsLoggedIn(true);
      this.router.navigate(["pick"]);
   }
}
