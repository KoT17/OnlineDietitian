import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { SignInService } from '../sign-in.service';

@Component({
  selector: 'app-pickdiet',
  templateUrl: './pickdiet.component.html',
  styleUrls: ['./pickdiet.component.css']
})
export class PickdietComponent implements OnInit {
  httpOptions = new HttpHeaders({
    "user": "",
    "password": "",
    "source": "pick"
  })

  constructor(private signInService: SignInService, private http: HttpClient, private router: Router) {
    this.httpOptions.set('user', signInService.getUser().email);
    this.httpOptions.set('password', signInService.getUser().password);
  }

  ngOnInit() {
  }

  select(option) {
    if(option == 1) {
      this.http.post("pickURL", { diet: ""}, { headers: this.httpOptions})
    } else {
      this.http.post("pickURL", { diet: ""}, { headers: this.httpOptions})
    }
    this.router.navigateByUrl('/authhome');
  }
}
